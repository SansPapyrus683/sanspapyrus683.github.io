const BLOCK_LEN = 3;

let editorial = document.getElementById("editorial").innerHTML;

let newEditorial = "";
let inlineClosing = false;
for (let i = 0; i < editorial.length; i++) {
    if (editorial.slice(i, i + BLOCK_LEN) === "```") {
        let block = "";
        let j = i + BLOCK_LEN;
        for (; editorial.slice(j, j + BLOCK_LEN) !== "```"; j++) {
            block += editorial.charAt(j);
        }

        let final = "";
        if (block.includes("\n")) {
            let lang = "";
            let code = "";
            let langState = true;
            for (let k = i + BLOCK_LEN; k < j; k++) {
                let c = editorial.charAt(k);
                if (c.trim() === "" && langState) {  // checks for whitespace
                    langState = false;
                } else if (langState) {
                    lang += c;
                } else {
                    code += c;
                }
            }

            let spaceNum = 0;
            for (let k = 0; k < code.length; k++) {
                let c = code.charAt(k);
                if (c.trim() !== "") {
                    break;
                } else {
                    spaceNum++;  // NOTE: assumes all whitespace is SPACES. NO TABS!!
                }
            }
            let lines = code.split("\n");
            if (lines[lines.length - 1].trim() === "") {
                lines.pop();
            }
            for (let l = 0; l < lines.length; l++) {
                lines[l] = lines[l].slice(spaceNum);
            }

            // don't worry if lang is empty- prism handles it just fine
            final += `<pre><code class="language-${lang}">`
            for (let l of lines) {
                final += l + "\n";
            }
            final += "</pre></code>"
        } else {
            final += `<pre><code class="language-">${block}</code></pre>`
        }
        newEditorial += final;
        i = j + BLOCK_LEN - 1;
    } else if (editorial.charAt(i) === "`") {
        if (inlineClosing) {
            newEditorial += "</span>"
        } else {
            newEditorial += "<span class=\"inline\">"
        }
        inlineClosing = !inlineClosing;
    } else {
        newEditorial += editorial.charAt(i);
    }
}

document.getElementById("editorial").innerHTML = newEditorial;
