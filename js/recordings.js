function resetMenu(menuItem) {
    menuItem.style.textDecoration = "none";
    menuItem.style.color = "black";
    menuItem.style.borderRight = "3px solid rgba(139, 96, 16, 0.95)";
}

function activeMenu(menuId) {
    var menuItem = document.getElementById(menuId);
    menuItem.style.textDecoration = "underline";
    menuItem.style.color = "rgba(107, 142, 35, 0.85)";
    menuItem.style.borderRight = "3px solid rgba(107, 142, 35, 0.85)";
}

function reset() {
    var i;
    var menu = document.getElementsByClassName("menu-item");
    for(i=0; i<menu.length; i++) {
        resetMenu(menu[i]);
    }
    var display = document.getElementsByClassName("display-item");
    for(i=0; i<display.length; i++) {
        display[i].style.display = "none";
    }
}

function mhwgo() {
    reset();
    activeMenu("menu-mhwgo");
    document.getElementById("display-mhwgo").style.display = "block";
}

function tmrdh() {
    reset();
    activeMenu("menu-tmrdh");
    document.getElementById("display-tmrdh").style.display = "block";
}

function pn() {
    reset();
    activeMenu("menu-pn");
    document.getElementById("display-pn").style.display = "block";
}

function sas() {
    reset();
    activeMenu("menu-sas");
    document.getElementById("display-sas").style.display = "block";
}