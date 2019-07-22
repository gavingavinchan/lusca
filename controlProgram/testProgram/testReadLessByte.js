var i2c = require('i2c');

device = new i2c(0x41, {device: '/dev/i2c-1'});
console.log('initiaited');

function readFromDevice(){
  device.readBytes(0x69, 3, function(err, data){
    if(err){
       console.log('error: '+ err);
    }
    console.log(data);
  });
}

setInterval( readFromDevice, 100);
