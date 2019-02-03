var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


exports.init = function(pingerAddr) {
  device = new i2c(pingerAddr, {device: '/dev/i2c-3'});
}


var pingResults = 0;
var voltage = 0;
socket.on('Ping', function() {
  pinger.device.readBytes(0x99, 2, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults = res;
    /*
    if(res[2]==0x00 && res[3]==0xFF){
      console.log(res[0] + "\t" + res[1]);
    }
    else{
      console.log("FAILED");
    }
    */
    var raw = (pingResults[0]<<8) | (pingResults[1]);
    console.log(res[0] + "\t" + res[1]);
    pinVoltage = raw/1024*5;
    inputVoltage = raw/1024*12;
    socket.emit('pingerPinVoltage', pinVoltage);
    socket.emit('pingerInputVoltage', inputVoltage);
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




function ping(){
  device.readBytes(0x99, 2, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults = res;
    console.log(res[0] + "\t" + res[1]);
  });
}

//setInterval(ping, 50);
