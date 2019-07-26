console.log('starting test program')
/*const express = require('express');
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
*/
var _messenger = require("./messenger.js");
var messenger = new _messenger.client({});


var pHTemp = require("./pHTemp.js");
pHTemp.init(0x35);

setInterval(function() {
  messenger.emit('pHTemp',0x69);
},500);


messenger.on('pH Value', function (pHByte) {
  console.log('0x69 pH: ' + pHByte);
});


messenger.on('Temp Value', function (tempByte) {
  console.log('0x69 temp: ' + tempByte);
});


messenger.on('miscError', function(message){
  console.log(message);
});
