const http = require('http');
const fs = require('fs');
const url = require('url');

const { exec } = require('child_process');

const port = process.env.PORT || 3000;
const pageNotFound_path = '/404.html';
const pagesURL = ['/index.html', '/projects.html', '/contact.html'];

const pageNotFound = (path, res) => {
    fs.readFile(__dirname + path, (err, data) => {
        if(err){
            res.writeHead(404);
            res.write('This page doesn\'t exist');
            res.end();
        } else {
            res.writeHead(404, {
                'Content-Type' : 'text/html',
            });
            res.write(data);
            res.end();
        }
    })
}

const server = http.createServer((req, res) => {
    const path = url.parse(req.url).pathname;
    if(path.includes('/assets/') || pagesURL.indexOf(path) != -1 || path === '/favicon.ico'){
        const extension = "text/" + path.slice(path.indexOf('.')+1, path.length);
        fs.readFile(__dirname + path, (err, data) => {
            if(err){
                pageNotFound(pageNotFound_path, res);
            }else{
                res.writeHead(200, {
                    'Content-Type' : extension,
                });
                res.write(data);
                res.end();
            }
        });
    }else if(path === "/"){
        res.writeHead(302, {
            location : "/index.html", 
        });
        res.end();
    }
    else{
        pageNotFound(pageNotFound_path, res);
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
