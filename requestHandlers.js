var BHMVC = require('./bhmvc');

function start(pathname, response) {
  console.log("Request handler 'start' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  response.write(BHMVC.foo(pathname));
  response.end();
}

function upload(pathname, response) {
  console.log("Request handler 'upload' was called.");
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.write("Hello Upload");
  response.end();
}
function bcp(pathname, response)
{
  console.log("Request handler 'upload' was called.");
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.write("Hello Upload");
  response.end();
}

exports.start = start;
exports.upload = upload;
exports.bcp = bcp;
