const http = require('http');
const fs = require('fs');
const url = require('url');

const { exec } = require('child_process');
//What's the best way to 
const allowedPaths = ["/index.xhtml", "/src/scriptsJs/index.js"];

const port = process.env.PORT || 3000;

const server = http.createServer((req, res) => {
    const path = url.parse(req.url).pathname;
    if(allowedPaths.indexOf(path) != -1){
        //Check if its extension and sent it as such
        console.log("Includes\n");
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
    }else if(path == "/"){
        console.log("Root\n");
        res.writeHead(302, {
            location : "/index.xhtml", 
        });
        res.end();
    }
    else{
        console.log("Non\n");
        res.writeHead(418);
        res.write("Unable to show page");
        res.end();
    }

    /*console.log(exec('ls -a', (err, stdout, stderr) => {
        if(err){
            console.log(`error: ${err.message}`);
            return;
        }
        if(stderr){
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`stdout: ${stdout}`);
    }));*/
});

server.listen(port, (error) => {
    if(error){
        console.log(`Something went wrong. ${error}`);
    }else{
        console.log(`Server listening on port ${port}`);
    }
});
