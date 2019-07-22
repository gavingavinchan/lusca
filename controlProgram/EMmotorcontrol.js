var i2c = require('i2c');

var _messenger = require("./messenger.js");
var messenger = new _messenger.client({});


module.exports = function(_settings){
  var EM = function() {};

  EM.setting = Object.assign({name: 'undefined', address: 0x00, }, _settings);

  const i2cdevice = new i2c(EM.setting.address, {device: '/dev/i2c-1'});


  //variable attraction strength
  messenger.on(EM.setting.name, function(_EM) {
    //console.log("EM1");

    if(_EM.side == "left") {
      //console.log("EM1: " + _EM.strength);
      i2cdevice.write([0x21, _EM.strength], function(err) {
        if(err) {messenger.emit('miscError', "0x" + EM.setting.address.toString(16) + ",EM.left: "  + err);}
      });
    } else if(_EM.side == "right") {
      i2cdevice.write([0x22, _EM.strength], function(err) {
        if(err) {messenger.emit('miscError', "0x" + EM.setting.address.toString(16) + "EM.right: " + err);}
      });
    } else {
      messenger.emit('miscError', 'EMmotorcontrol.js: EM error, so left or right?');
    }
  });

  return EM;
}
