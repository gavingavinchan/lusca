var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');

var pinger = {};
exports.init = function(pingerAddr) {
  pinger.device = new i2c(pingerAddr, {device: '/dev/i2c-1'});
}


var pingResults = 0;
var voltage = 0;
socket.on('Ping', function() {
  pinger.device.readBytes(0x95, 4, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults = res;
    if(res[2]==0x00 && res[3]==0xFF){
      console.log(res[0] + "\t" + res[1]);
    }
    else{
      console.log("FAILED");
    }
    /*
    console.log(res[0] + "\t" + res[1]);
    var raw = (pingResults[0]<<8) | (pingResults[1]);
    pinVoltage = raw/1024*5;
    inputVoltage = raw/1024*12;
    socket.emit('pingerPinVoltage', pinVoltage);
    socket.emit('pingerInputVoltage', inputVoltage);
    */
  });

})
