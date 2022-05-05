const http = require('http');
const url = require('url');
const fs = require('fs');
const path = require('path');

const port = process.env.PORT || 3000;

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
    // console.log(`${req.method} ${req.url}`);

    const parsedUrl = url.parse(req.url);
    let pathname = `.${parsedUrl.pathname}`;
    const ext = path.parse(pathname).ext;
    const map = {
      '.ico': 'image/x-icon',
      '.html': 'text/html',
      '.js': 'text/javascript',
      '.json': 'application/json',
      '.css': 'text/css',
      '.png': 'image/png',
      '.jpg': 'image/jpeg',
      '.wav': 'audio/wav',
      '.mp3': 'audio/mpeg',
      '.svg': 'image/svg+xml',
      '.pdf': 'application/pdf',
      '.doc': 'application/msword'
    };
  
    fs.exists(pathname, function (exist) {
      if(!exist) {
        // if the file is not found, return 404
        res.statusCode = 404;
        res.end(`File ${pathname} not found!`);
        return;
      }
  
      // if is a directory search for index file matching the extension
      if (fs.statSync(pathname).isDirectory()) pathname += '/index' + ext;
  
      fs.readFile(pathname, function(err, data){
        if(err){
          res.statusCode = 500;
          res.end(`Error getting the file: ${err}.`);
        } else {
          res.setHeader('Content-type', map[ext] || 'text/plain' );
          res.end(data);
        }
      });
    });
  

    // const path = url.parse(req.url).pathname;
    // const extension = path.slice(path.indexOf('.')+1, path.length);
    // fs.readFile(__dirname + path, (err, data) => {
    //     console.log(req.headers);
    //     if(err){
    //         pageNotFound(pageNotFound_path, res);
    //     }else{
    //         if(extension == "pdf" || extension == "xml"){
    //             res.writeHead(200, {
    //                 'Content-Type' : "application/" + extension,
    //             });
    //         }
    //         else{
    //             res.writeHead(200, {
    //                 'Content-Type' : "text/" + extension,
    //             });
    //         }
    //         res.write(data);
    //         res.end();
    //     }
    // });
    // if(path === "/"){
    //     res.writeHead(302, {
    //         location : "/index.html", 
    //     });
    //     res.end();
    // }
    // else{
    //     pageNotFound(pageNotFound_path, res);
    // }
});

server.listen(port, (error) => {
    if(error){
        console.log(`Something went wrong. ${error}`);
    }else{
        console.log(`Server listening on port ${port}`);
    }
});
