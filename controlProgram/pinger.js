var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');

var pinger = {};
exports.init = function(pingerAddr) {
  pinger.device = new i2c(pingerAddr, {device: '/dev/i2c-1'});
}


var pingResults = 0;
socket.on('ping', function() {
  pinger.device.readBytes(0x99, 16, function(err,res) {
    pingResults = res;
  });
  console.log("Ping Results: " + pingResults);
  socket.emit('pingResults', pingResults);
})
