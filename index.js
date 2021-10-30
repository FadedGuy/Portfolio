const http = require('http');
const fs = require('fs');
const url = require('url');

const { exec } = require('child_process');

const port = process.env.PORT || 3000;

const server = http.createServer((req, res) => {
    const path = url.parse(req.url).pathname;
    fs.readFile(__dirname + path, (err, data) => {
        if(err){
            res.writeHead(404);
            res.write('This page doesn\'t exist');
            res.end();
        }else{
            res.writeHead(200, {
                'Content-Type' : 'text/html'
            });
            res.write(data);
            res.end();
        }
    });
});

server.listen(port, (error) => {
    if(error){
        console.log(`Something went wrong. ${error}`);
    }else{
        console.log(`Server listening on port ${port}`);
    }
});
