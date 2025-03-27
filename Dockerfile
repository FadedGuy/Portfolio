FROM node:18.20.8-alpine3.21 AS build

WORKDIR /app

COPY package.json package-lock.json ./

RUN npm install

COPY . .

RUN npm run build --prod

FROM nginx:stable-alpine3.20-perl
# Issue with Angular requires to add /browser to output dir
# https://github.com/angular/angular-cli/issues/26304
COPY --from=build /app/dist/portfolio/browser /usr/share/nginx/html