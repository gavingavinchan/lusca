var server = function(setting) {
  const express = require('express');
  const app = express();
  var http = require('http').Server(app);
  var io = require('socket.io')(http);
  app.use(express.static('public'));
  app.get('/', (req, res) => {
  	res.send('Hello Express app');
  });


  io.on('connection', function(socket) {
    // log socket communications
/*
    socket.use((packet, next) => {
      console.log(new Date() + '\t' + packet[0] + '\t' + packet[1]);
      return next();
    });

*/
    // relay messages from clients
    socket.use((packet, next) => {
      io.emit(packet[0], packet[1]);
      return next();
    });
  });
  http.listen(80, function() {
    console.log('listening on *:80 ');
  });
}





var client =  function(setting){
  var io = require('socket.io-client');
  var socket = io.connect('http://localhost:80');
  var c = function() {};
  c.emit = function(channel,message) {
    //console.log("emit " + channel + ": " + message);
    return socket.emit(channel,message);
  },

  c.on = function(channel,message) {
    /*
      var a = socket.on(channel,message);
      console.log("on " + a);
      return a;*/
      return socket.on(channel,message);
   }

  return c;
}


module.exports = {
  client : client,
  startServer: server
}
