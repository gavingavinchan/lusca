var _messenger = require("./dummyMessenger.js");
var messenger = new _messenger.client({});

messenger.on('message', function(value) {
  console.log("Message: " + value);
})
messenger.on('message', function(value) {
  console.log("Message2: " + value);
})

messenger.emit('message', "This is the message");
console.log("Emitted");
