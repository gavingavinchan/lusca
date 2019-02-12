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
  EM.socket.on(EM.setting.name, function(value) {
    let name = EM.setting.name;
    if(name.indexOf("left")) {
      i2cdevice.writeBytes(0x21, [strength], function(err) {
      console.error(err);
    } else if(name.indexOf('right') {
      i2cdevice.writeBytes(0x22, [strength], function(err) {
      console.error(err);
    } else {
      console.log('EM error, so left or right?');
  })

  return EM;
}


