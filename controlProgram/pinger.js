var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


exports.init = function(pingerAddr) {
  device = new i2c(pingerAddr, {device: '/dev/i2c-1'});
}


var pingResults = [];
var voltage = 0;
socket.on('Ping', function() {
  ping();
 // console.log("ping: " + pingResults);
  var raw = (pingResults[0]<<8) | (pingResults[1]);
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
})




function ping(){
  device.write([0x99], function(err) {
    if (err){
      console.log("error reading" + err);
      return;
    }
  });

  device.read(1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults[0] = res[0]
  });


  device.read(1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults[1] = res[0];
  });


}

//setInterval(ping, 50);
