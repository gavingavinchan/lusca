var i2c = require('i2c');

var device = new i2c(0x35, {device: '/dev/i2c-1'});

function read(){

  device.readBytes(0x69, 4, function(err, res){

    if (err) return;

    var output = '';
    for (var x of res){
      output +=  x + '\t';
    }
    console.log(output);
  });
}

setInterval( read, 2000);
