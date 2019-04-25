var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');

var CAMController = {};
exports.init = function(CAMControllerAddr) {
  CAMController.device = new i2c(CAMControllerAddr, {device: '/dev/i2c-1'});
}

var servo = function(command,servoMicros) {
  CAMController.device.writeBytes(command, [servoMicros >>> 8, servoMicros%255], function(err) {
    if(err) {socket.emit('miscError', "CameraControlo," + command + "," + servoMicros + ": " + err);}
  });
}

socket.on('servo', function(_servo) {
  servo(_servo.command, _servo.micros);
  //console.log(_servo.command);
  //console.log(_servo.micros);
})
