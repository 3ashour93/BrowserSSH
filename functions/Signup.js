var bcrypt = require('bcrypt-nodejs');
var sqlite3 = require('sqlite3').verbose();
var users = new sqlite3.Database('users.db');

function signup (username, password, done) {
  users.serialize(function() {    
    users.run("CREATE TABLE users (user TEXT, password TEXT)", [], 
      function (err) {});

    var finder = users.prepare("SELECT user FROM users WHERE user = (?)")
    finder.get (username, [], function(err,row) {
        if (row != undefined) {
          finder.finalize();
          done(false)
        }

        else {
          var inserter = users.prepare("INSERT INTO users (user, password) VALUES (?, ?)");
          inserter.run (username, bcrypt.hashSync(password));
          inserter.finalize();
          finder.finalize();
          done(true);
        }
    })
  });
};

module.exports =  signup