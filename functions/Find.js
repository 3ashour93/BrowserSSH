var bcrypt = require('bcrypt-nodejs');
var sqlite3 = require('sqlite3').verbose();
var users = new sqlite3.Database('users.db');

function find (id, done) {
  users.serialize(function() {
    users.run("CREATE TABLE users (user TEXT, password TEXT)", [], 
      function (err) {});

    var finder = users.prepare("SELECT user FROM users WHERE rowid = (?)")

    finder.get (id, [], function(err,row) {
        if (row == undefined){
            done (null, false)
          }

        else done (null, row.user)
    })
    finder.finalize();
  });
};

module.exports =  find