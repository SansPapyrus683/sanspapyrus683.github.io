// TODO: maybe add support for ``` as well?
let editorial = document.getElementById("editorial").innerHTML;

console.log("what");

let newEditorial = "";
let closing = false;
for (let i = 0; i < editorial.length; i++) {
    if (editorial.charAt(i) === "`") {
        if (closing) {
            newEditorial += "</span>"
        } else {
            newEditorial += "<span class=\"inline\">"
        }
        closing = !closing;
    } else {
        newEditorial += editorial.charAt(i);
    }
}

document.getElementById("editorial").innerHTML = newEditorial;
