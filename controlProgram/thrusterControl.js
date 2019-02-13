var i2c = require('i2c');
var io = require('socket.io-client');


const timeInterval = 50;
const maxAccelerationPerSecond = 0.5;
const maxStepPerInterval = maxAccelerationPerSecond * (timeInterval/1000);


var i2cThrusterWrite = function(device, _currentSpeed) {
  var speed = parseInt(_currentSpeed * 32767);
  var hb = (speed >>> 8) & 0xFF;
  var lb = speed % 255;
  device.writeBytes(0x00, [hb, lb], function(err) {
    if (err){
      //console.log(device.address);
      //console.log("error in thruster: " + speed + "\t" + hb + "\t" + lb);
    }
  });
}

module.exports = function(setting){

  var thruster = function() {};

  // INIT Thruster
  thruster.setting = Object.assign({ name: 'undefined', address: 0x00, invert: false }, setting);
  thruster.socket = io.connect('http://localhost:80');
  thruster.started = false;

  const device = new i2c(thruster.setting.address, {device: '/dev/i2c-1'});
  console.log(thruster.setting);
  var currentSpeed = 0,
    targetSpeed= 0,
    invert= thruster.setting.invert ? -1 : 1;

  var loop = 0;

  thruster.start = function(){
    if(thruster.started) return;
    thruster.started = true;

    //console.log(thruster.setting.name);
    i2cThrusterWrite(device,0);
    loop = setInterval(() => {
      if(Math.abs(targetSpeed-currentSpeed) > maxStepPerInterval) {
        if(targetSpeed > currentSpeed) {
          //console.log("positive acceleration too high.   " + "currentSpeed: " + t.currentSpeed + " newSpeed: " + newSpeed);
          currentSpeed += maxStepPerInterval;
        } else {
          currentSpeed -= maxStepPerInterval;
          //console.log("negative acceleration too low.   " + "currentSpeed: " + t.currentSpeed);
        }
      } else {
        currentSpeed = targetSpeed;
      }
      // console.log("cs: " + currentSpeed);

      // truncate
      if(Math.abs(currentSpeed) > 1) {
        if(currentSpeed>0) {currentSpeed = 1} else {currentSpeed = -1};
      }

      thruster.socket.emit('thruster.thrust.'+ thruster.setting.name, currentSpeed);
      i2cThrusterWrite(device, invert * currentSpeed);
    }, timeInterval);
  }

  thruster.socket.on('thrusterControl.start', function() {
    console.log("thrusterstarts");
    thruster.start();
    thruster.socket.emit('thruster', thruster.setting.name + ': starting thruster');
  });

  thruster.stop = function(){
    i2cThrusterWrite(device, 0);
    clearInterval(loop);
  }

  thruster.socket.on('thrusterControl.stop', function() {
    thruster.stop();
  })



  thruster.thrust = function(power){
    targetSpeed = power;
  }

  thruster.socket.on('thrusterTarget.'+ thruster.setting.name, function(power) {
    thruster.thrust(power);
  });

  return thruster;
};
