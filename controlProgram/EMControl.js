//TODO: give name to objects and then pubsub
var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


module.exports = function(_settings){
  var EM = function() {};

  EM.setting = Object.assign({name: 'undefined', address: 0x00, }, _settings);
  EM.socket = io.connect('http://localhost:5000');

  const i2cdevice = new i2c(EM.setting.address, {device: '/dev/i2c-1'});


  //variable attraction strength
  socket.on(EM.setting.name, function(_EM) {
    //console.log("EM1");
    if(_EM.side == "left") {
      //console.log("EM1: " + _EM.strength);
      i2cdevice.writeBytes(0x21, [_EM.strength], function(err) {
        socket.emit('miscError', err);
      });
    } else if(_EM.side == "right") {
      i2cdevice.writeBytes(0x22, [_EM.strength], function(err) {console.error(err);});
    } else {
      console.log('EMContorl.js: EM error, so left or right?');
    }
  });

  return EM;
}


