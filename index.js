var router = require("./router");
var requestHandlers = require("./requestHandlers");
var util = require('util');
var cpphello = require('./index');
var http = require("http").createServer(onRequest);
var url = require("url");
var io = require('socket.io').listen(http);
var BHMVC = require('./bhmvc');

http.listen(80);

function onRequest(request, response) {
    var pathname = url.parse(request.url).pathname;
    console.log("Request for " + pathname + " received.");

    router.route(handle,pathname, response);

    response.writeHead(200, {"Content-Type": "text/plain"});
    response.write("Hello World");
    response.end();
}

var handle = {}
handle["/"] = requestHandlers.start;
handle["/start"] = requestHandlers.start;
handle["/welcome/WelcomeMsg"] = requestHandlers.start;
handle["/index"] = requestHandlers.start;
handle["/upload"] = requestHandlers.upload;

io.sockets.on('connection', function (socket) {
  socket.emit('connection',JSON.parse(BHMVC.foo("/welcome/values")));
  socket.on('getUserName', function (data) {
    if(io.sockets.clients('room1').length == 0)
    {
        socket.join('room1');
        socket.broadcast.to('room1').emit('roomStatus', 
            { 'message': data['name'] + ' has joined the room', 
              'numPeople' : 1 });
        socket.emit('roomStatus', 
            { 'message': data['name'] + ' has joined the room', 
              'numPeople' : 1 });
        console.log("joining room, theres 1 person");
    }
    else if(io.sockets.clients('room1').length == 1)
    {
        console.log(data.name + ' has joined the room.');
        socket.join('room1');
        socket.broadcast.to('room1').emit('roomStatus', 
            { 'message': data['name'] + ' has joined the room', 
              'numPeople' : 2 });
        socket.emit('roomStatus', 
            { 'message': data['name'] + ' has joined the room', 
              'numPeople' : 2 });
    }
    else
    {
        socket.emit('roomStatus', 'full'); 
        console.log('room is full');
    }
  });
  socket.on("clientMsg", function(msg) { 
    socket.broadcast.emit('serverMsg',msg);
    console.log("clientMsg received");
    });
  socket.on("disconnect", function(msg){
    socket.leave('room1');
    console.log('A client is leaving room 1');
  });
});
