'use strict'

window.addEventListener('load', load_content);
let prefLanguageprefix = "en";

function html([str, ...strs], ...vals) {
    return strs.reduce((acc,v,i)=> acc+vals[i]+v, str);
}

function click(click_id){
    let t1 = document.getElementById('t1');
    let t2 = document.getElementById('t2');
    let t3 = document.getElementById('t3');
    let t4 = document.getElementById('t4');

    if(t1 === null || t2 === null || t3 === null || t4 === null){
        return;
    }

    if(click_id != "t1"){
        t1.className = "t1";
    }
    if(click_id != "t2"){
        t2.className = "t2";
    }
    if(click_id != "t3"){
        t3.className = "t3";
    }
    if(click_id != "t4"){
        t4.className = "t4";
    }
}

function click_t1(){
    let t1 = document.getElementById('t1');
    let extra = document.getElementById('extra');
    if(t1 === null || extra === null){
        return;
    }

    click("t1")

    if(t1.className === "t1"){
        t1.className = "t1 show";
        extra.className = "dissapear";
    }
    else{
        t1.className = "t1";
        extra.className = "";
    }
}

function click_t2(){
    let t2 = document.getElementById('t2');
    let extra = document.getElementById('extra');
    if(t2 === null || extra === null){
        return;
    }

    click("t2")

    if(t2.className === "t2"){
        t2.className = "t2 show";
        extra.className = "dissapear";
    }
    else{
        t2.className = "t2";
        extra.className = "";
    }
}

function click_t3(){
    let t3 = document.getElementById('t3');
    let extra = document.getElementById('extra');
    if(t3 === null || extra === null){
        return;
    }

    click("t3")

    if(t3.className === "t3"){
        t3.className = "t3 show";
        extra.className = "dissapear";
    }
    else{
        t3.className = "t3";
        extra.className = "";
    }
}

function click_t4(){
    let t4 = document.getElementById('t4');
    let extra = document.getElementById('extra');
    if(t4 === null || extra === null){
        return;
    }

    click("t4")

    if(t4.className === "t4"){
        t4.className = "t4 show";
        extra.className = "dissapear";
    }
    else{
        t4.className = "t4";
        extra.className = "";
    }
}

function change_name(){
    let nameTag = document.getElementById('name');
    if(nameTag === null){
        return;
    }

    nameTag.textContent === "Faded" ? nameTag.textContent = "Kevin" : nameTag.textContent = "Faded";
}

function load_content(){
    let body = document.getElementById('wrapper');
    if(body === null){
        return;
    }

    // Crappy way to determine pref language to display default english
    let prefLanguage = navigator.language;
    if(prefLanguage.startsWith("es")){
        prefLanguageprefix = "es";        
    }
    else if(prefLanguage.startsWith("fr")){
        prefLanguageprefix = "fr";
    }
    
    body.innerHTML = html`
        ${language[prefLanguageprefix]}
    `;

    setInterval(change_name, 2000);
    start();
}