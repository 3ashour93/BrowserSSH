process.on('uncaughtException', function (err) {

    console.log(err);

});



/*

 * Module dependencies

 */

var express = require('express')

  , bodyParser = require("body-parser")

  , sys = require("sys")

  , Connection = require('ssh2')

  , ansi_up = require('ansi_up')

  , fs = require('fs')

  , ph = require('path');





/* 

 * Initializing the app and setting up socketio

 */

var app = express();

var port = process.env.PORT || 3000;

var server = app.listen(port);

var io = require('socket.io').listen(server)



// This tells express where my views are.

app.set('views', __dirname + '/views')



// This tells express that it will be rendering ejs files.

app.set('view engine', 'ejs');



app.use(express.bodyParser());



// app.router is what deals with app.get and app.post requests.

app.use(app.router);

app.use(express.logger('dev'))



/*  

 *  both of these do the same thing, but express keeps changing its docs

 *  so this ensures that it will find the files. 

 */

app.use(express.static('public')); 

app.use(express.static(__dirname + '/public'))

app.use(bodyParser.urlencoded({ extended: false }));



/*

 * Route

 */

app.get('/',

        function (request, response) {

            response.render('terminal-page')

});





// Takes a cd command and adds/removes from the path accordingly.

function parseCd (path, cd) {

  cdA = cd.split("/");

  console.log(cdA);

  for (x in cdA) {

    console.log(cdA[x]+'\n');

    if (cdA[x] == '..') {

      return;

      // saw = 0;

      // while (saw == 0){

      //   if (path[-1] == '/') saw = 1;

      //   path = path.slice(0, -1);

      // }

    }



    else path += (cdA[x] + '/');

  }



  return path;

}



// if a client want to connect, a connection event triggers.

io.on('connection', function(socket){

  console.log(socket.id);



  /*

   * a client emits 'login' if they want to connect to an ssh server.

   */

  socket.on('login', function(info){

    var username = info['user']

    var password = info['pass']

    var host = info['host']



    var conn = new Connection();

    conn.connect({

      host: host,

      port: 22,

      username: username,

      password: password

    });



    conn.on('ready', function() {



      // Shell that will do all of the clients' commands.

      conn.shell(function(err, stream) {

        if (err) throw err;



        // client sends disconnect if the user closes the page.

        socket.on('disconnect', function() {

          conn.end();

        })



        stream.stderr.on('data', function(data) {

            console.log('STDERR: ' + data);

        });



        // client sends cmd if he wants to run some command on the server.

        socket.on('cmd', function (command) {

            console.log(command);

            if (command.indexOf("emacs") != -1 ||

                command.indexOf("vi") != -1 || 

                command.indexOf('vim') != -1)

              return;

            stream.write(command + "\n");

        });

        

        // data from the ssh connection.

        stream.on('data', function(data) {

          console.log('STDOUT1: ' + data);

          var returned = data.toString();

          var returned = ansi_up.ansi_to_html(returned);

          var returned = returned.replace('\r\r\n',"<br/>");

          socket.emit('output', returned);

        });

      });



      /*

       *  Shell that will only keep track of the path and do stuff that the

       *  user doesnt specifically ask for. It will also do commands that might

       *  cause a race condition if done in the clients' shell.

       */

      conn.shell(function(err, stream) {

        if (err) throw err;



        var path = "";

        var list = 0;



        socket.on('disconnect', function() {

          conn.end();

        });



        stream.stderr.on('data', function(data) {

            console.log('STDERR: ' + data);

        });



        socket.on('cmd', function (command) {

            console.log(command);

            if (command.indexOf("cd") == 0){ // it only cds, path keeping.

              path = parseCd(path, command.slice(3));

              console.log (path);

              stream.write(command + "\n");

            }

            else if (command.indexOf("emacs") != -1 ||

                command.indexOf("vi") != -1 || 

                command.indexOf('vim') != -1) {

              console.log('EDITOR MODE');

              var splitCom = command.split(" ");

              var file = splitCom[1];

              conn.sftp(function(err, sftp) {

              if (err) try {} catch (err) {console.log(err)};

              fs.writeFile('files/' + username + "-bssh-" + file, '') // cheap way to create a file

              var localPath = ph.join('files', username + "-bssh-" + file);

              console.log(localPath);

              sftp.fastGet(path + file, localPath, function(err) {

                if (err) 

                  try {} 

                  catch (err) {

                    socket.emit('noSuchFile', file);

                    return;

                  }



              else {

                fs.readFile (localPath, 'utf8', function (err, data) {

                  if (err) throw err;



                  socket.emit('file', {'data_in': data, 'name': file, 'path': path})

                });

              }

            });

          });

        }

      });



        stream.on('data', function(data) {

          console.log('STDOUT2: ' + data);



          // If list == 1 then it is the output of the command ls --file-type.

          if (list == 1) {

            data = data.toString();

            socket.emit('FileList', ansi_up.ansi_to_html(data));

            list--;

          }



          // If it is 2 then it is the input string returned by the ssh connection.

          else if (list == 2) { list--; }

        });



        // sends ls --file-type to get the list of files/folders.

        socket.on('getFileList', function() {

          console.log("getting file list");

          stream.write("ls --file-type\n");

          list = 2;

        });



        // opens sftp connection and saves the file to the ssh server.

        socket.on('saveFile', function(fileInfo) {

          console.log("got file");

          conn.sftp(function(err, sftp) {

            if (err) try {} catch (err) {console.log(err)};

            console.log(fileInfo['data']);

            var localPath = ph.join("files/", username + "-bssh-" + fileInfo['name']);

            fs.writeFile(localPath, fileInfo['data']);

            console.log('LOCAL PATH IS');

            console.log(localPath);

            console.log('SERVER PATH');

            console.log(fileInfo['path'] + fileInfo['name']);

            // sftp.fastPut(localPath, fileInfo['path'] + fileInfo['name'], function(err) {

            //   if (err) 

            //     try {} 

            //     catch (err) {

            //       console.log(err);

            //       socket.emit('noSuchFile', file);

            //       return;

            //     }

            // })

            fs.readFile (localPath, 'utf8', function (err, data) {

                  if (err) throw err;



                  stream2 = sftp.createWriteStream (fileInfo['path'] + fileInfo['name'])

                  stream2.write (data);

                  stream2.end(); 

                });

          })

        });

      });

    });

  });

});

