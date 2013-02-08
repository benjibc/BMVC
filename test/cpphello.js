var
  util = require('util'),
  cpphello = require('../index');

var http = require("http");

http.createServer(function(request, response) {
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.write(cpphello.foo());
    response.end();
}).listen(8888);

console.log(cpphello.foo());
console.log(util.inspect(cpphello, true, null));
