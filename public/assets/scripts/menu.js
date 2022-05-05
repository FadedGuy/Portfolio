'use strict';

window.addEventListener('load', insert_menu);

function html([str, ...strs], ...vals) {
    return strs.reduce((acc,v,i)=> acc+vals[i]+v, str);
}

function insert_menu(){
    let div = document.getElementById('menu-div');

    if(div === null){
        return null;
    }

    div.innerHTML = html`
        <input type="checkbox" class="toggler">
        <div class="hamburger"><div></div></div>
        <div class="menu">
            <div>
                <div>
                    <ul>
                        <li><a href="index.html" ${document.URL.endsWith("/index.html") ? `class="selected"` : ``}>Home</a></li>
                        <li><a href="projects.html" ${document.URL.endsWith("/projects.html") ? `class="selected"` : ``}>Projects</a></li>
                        <li><a href="contact.html" ${document.URL.endsWith("/contact.html") ? `class="selected"` : ``}>Contact</a></li>
                        <br>
                        <span class="icons">
                            <a class="fa fa-github" href="https://github.com/FadedGuy"></a>
                            <a class="fa fa-linkedin" href="https://www.linkedin.com/in/kevin-damian-aceves-siordia-679a47156"></a>
                            <a class="fas fa-egg" href="404.html"></a>
                        </span>
                    </ul>
                </div>
            </div>
        </div>
        `;
}