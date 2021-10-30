const http = require('http');
const fs = require('fs');
const url = require('url');

const { exec } = require('child_process');

const port = process.env.PORT || 3000;

const server = http.createServer((req, res) => {
    const path = url.parse(req.url).pathname;
    //Redirect __dirname to /index.xhtml
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
