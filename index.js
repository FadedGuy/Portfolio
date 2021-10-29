const http = require('http');
const fs = require('fs');

// const hostname = '127.0.0.1';
const port = process.env.PORT || 3000;

const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    fs.readFile('index.xhtml', (error, data) => {
        if(error){
            res.writeHead(404);
            res.write(`Error: file not found`);
        } else {
            res.write(data);
        }
        res.end();
    });
});

server.listen(port, (error) => {
    if(error){
        console.log(`Something went wrong. ${error}`);
    }else{
        console.log(`Server listening on port ${port}`);
    }
});