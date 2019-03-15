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

var pHTemp = require("./pHTemp.js");
pHTemp.init(0x70);

setInterval(function() {
  //0x67 0x68 do also
  io.emit('pHTemp', 0x69);
},50);

socket.on('pH Value', function(pHByte) {
  console.log(pHByte);
})

socket.on('Temp Value', function(tempByte) {
  console.log(tempByte);
})
