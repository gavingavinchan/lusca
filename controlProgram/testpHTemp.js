console.log('starting test program')
const express = require('express');
const app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
app.use(express.static('public'));
app.get('/', (req, res) => {
	res.send('Hello Express app');
});


io.on('connection', function(socket) {
  // relay messages from clients
  socket.use((packet, next) => {
    io.emit(packet[0], packet[1]);
    return next();
  });
});
http.listen(80, function() {
  //console.log('listening on *:80 ');
});



var pHTemp = require("./pHTemp.js");
<<<<<<< Updated upstream
pHTemp.init(0x48);
=======
pHTemp.init(0x64);
>>>>>>> Stashed changes

setInterval(function() {
  io.emit('pHTemp',0x69);
},200);

<<<<<<< Updated upstream
io.on ('connection', function(socket) {
	socket.on('pH Value', function(pHByte) {
  console.log(pHByte);
	});
});

io.on ('connection', function(socket){
	socket.on('Temp Value', function(tempByte) {
  console.log(tempByte);
	});
});
=======
io.on('connection', function(socket) {
socket.on('pH Value', function (pHByte) {
  console.log('0x69 pH: ' + pHByte);
	});
});

io.on('connection', function (socket) {
  socket.on('Temp Value', function (tempByte) {
    console.log('0x69 temp: ' + tempByte);
	});
});

io.on('miscError', function(message){
  console.log(message);
});
>>>>>>> Stashed changes
