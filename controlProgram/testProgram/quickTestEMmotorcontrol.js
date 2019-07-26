var i2c = require('i2c');
var address = 0x09;
var wire = new i2c(address, {device: '/dev/i2c-1'}); // point to your i2c address, debug provides REPL interface


wire.scan(function(err, data) {
  if(err) {
    console.log("cant scan: " + err);
    return;
  }
  console.log("scan: " + data);
});

var i=0;
var j=120;

setInterval( () => {
  i += 10;
  j += 10;
  if (i>255) i=0;
  if (j>255) j=0;
  wire.write([0x22, i], function(err) {
    if(err) {
      console.log("cant write: " + err);
      return;
    }
    console.log("0x22 write: " + i);
  });

  wire.write([0x21, j], function(err) {
    if(err) {
      console.log("cant write: " + err);
      return;
    }
    console.log("0x21 write: " + j);
  });
/*
  wire.read(1, function(err, res) {
    if(err) {
      console.log("read err: " + err);
      return;
    }
    console.log("read: " + res);
  });
  */
/*
  wire.writeBytes(0x90, [i, j], function(err) {
    if(err) {
      console.log("write 0x90 err: " + err);
      return;
    }
    console.log("send: " + i + "," + j);
    wire.readBytes(0x90, 2,function(err,res) {
      if (err) {
        var errorMessage = "error reading" + err;
        console.log('echoerError', errorMessage);
        //console.log("error reading" + err);
        return;
      }
      if (res.length>1)
        console.log("received: " + parseInt(res[0]) + " "  + parseInt(res[1]));
      else
        console.log("received: " + parseInt(res[0]));
    });
  });
*/

}, 500);
