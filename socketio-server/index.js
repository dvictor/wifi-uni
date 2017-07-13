#!/usr/bin/env node

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var light = {state:false};
port = 8005

// app.get('/', function(req, res) {
//   console.log('index.html');
//   res.sendFile(__dirname + '/index.html');
// });

io.on('connection', function(socket) {
  console.log('User connected: ' + socket.id);
  var t0 = Date.now();

  socket.on('event-a', function (n) {
    //console.log('event-a: ' + n);
    if (n == 1000) {
      console.log(Date.now() - t0);
      return;
    }


    socket.emit('event');
  });
  socket.emit('event');

  /*socket.emit('light', light);
  socket.on('disconnect', function(){
    console.log('User disconnected: ' + socket.id);
  });
  socket.on('toggle', function(state) {
    light.state = !light.state;
    console.log('id: ' + socket.id + ' light: ' + light.state);
    io.sockets.emit('light', light);
  });*/

});

http.listen(port, function() {
  console.log('listening on *:'+port);
});
