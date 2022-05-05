'use strict';

window.addEventListener('load', main);

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

        card.innerHTML += html`
            <div class="project-card">
                <div class="card-head">
                    <p class="card-title">${repo.name}</p>
                    <a class="card-link" href="${repo.html_url}" target="blank">${repo.html_url}</a>
                </div>
                <div class="card-body">
                    <p class"="card-realme">${repo.description !== null ? repo.description : "No description available"}</p>
                    <br>
                    <div class="card-tags">
                        <span class="card-tag">Erlang</span>
        `;

        arr_langs.forEach(lang => {
            console.log(lang);
        });      

        card.innerHTML += html`
        </div></div></div>
        `;

        console.log("")
    });

}

function main(){
    https_get_github("fadedguy").then(json => {
        let div_cards = get_div();
        let cards = "";

        if(div_cards === null){
            return null;
        }

        div_cards.innerHTML = "";

        json.forEach(repo => {
            lang_array(repo, div_cards).then(lang => {
                console.log();
            })
        });

        console.log(json);
    });
}
