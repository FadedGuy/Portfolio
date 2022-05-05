'use strict';

window.addEventListener('load', main);

const dict_langs ={
    "BibTeX" : "bibtex",
    "C++" : "cpp",
    "C#" : "csharp",
    "C" : "c",
    "CSS" : "css",
    "HTML" : "html",
    "JavaScript" : "js",
    "Other" : "other",
    "Processing" : "processing",
    "Procfile" : "procfile",
    "Python" : "py",
    "SCSS" : "scss",
    "TeX" : "tex",
    "TypeScript" : "ts",
};

function get_div(){
    return document.getElementById('app');
}

async function https_get_github(user){
    const response = await fetch(`https://api.github.com/users/${user}/repos`);
    const json_response = await response.json();
    return json_response;
}

async function get_languages(url){
    const response = await fetch(url);
    const json_response = await response.json();
    return json_response;
}

async function lang_array(repo, card){
    get_languages(repo.languages_url).then(langs => {
        const arr_langs = Object.entries(langs);
        let card_tags = ""
        
        arr_langs.forEach(lang => {
           card_tags += `
                <span class="card-tag lang-${dict_langs[lang[0]]}">${lang[0]}</span>
           `;
        });      

        card.innerHTML += html`
            <div class="project-card">
                <div class="card-head">
                    <p class="card-title">${repo.name}</p>
                    <a class="card-link" href="${repo.html_url}" target="blank">${repo.html_url}</a>
                </div>
                <div class="card-body">
                    <p class"="card-description">${repo.description !== null ? repo.description : "No description available"}</p>
                    <br>
                    <div class="card-tags">
                        ${card_tags}
                    </div>
                </div>
            </div>
        `;
    });
}

function main(){
    https_get_github("fadedguy").then(json => {
        let div_cards = get_div();

        if(div_cards === null){
            return null;
        }

        div_cards.innerHTML = "";
        json.forEach(repo => {
            lang_array(repo, div_cards);
        });
    });
}
