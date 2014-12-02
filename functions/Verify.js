var bcrypt = require('bcrypt-nodejs');
var sqlite3 = require('sqlite3').verbose();
var users = new sqlite3.Database('users.db');

function verify (username, password, done) {
  users.serialize(function() {
    users.run("CREATE TABLE users (user TEXT, password TEXT)", [], 
      function (err) {});

    var finder = users.prepare("SELECT rowid AS id, password FROM users WHERE user = (?)")

    finder.get (username, [], function(err,row) {
        if (row == undefined || !bcrypt.compareSync(password, row.password)) {
            finder.finalize();
            done (null, false)
           }

        else {
          finder.finalize();
          done (null, row);
        }
    })
  });
};

module.exports =  verify