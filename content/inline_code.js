const BLOCK_LEN = 3;

const text = document.body.innerHTML;

let newText = "";
let inlineClosing = false;
for (let i = 0; i < text.length; i++) {
    if (text.slice(i, i + BLOCK_LEN) === "```") {
        let block = "";
        let j = i + BLOCK_LEN;
        for (; text.slice(j, j + BLOCK_LEN) !== "```"; j++) {
            block += text.charAt(j);
        }

        let final = "";
        if (block.includes("\n")) {
            let lang = "";
            let code = "";
            let langState = true;
            for (let k = i + BLOCK_LEN; k < j; k++) {
                let c = text.charAt(k);
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
            final += "</code></pre>"
        } else {
            final += `<pre><code class="language-">${block}</code></pre>`
        }
        newText += final;
        i = j + BLOCK_LEN - 1;
    } else if (text.charAt(i) === "`") {
        if (inlineClosing) {
            newText += "</code>"
        } else {
            newText += "<code class=\"inline\">"
        }
        inlineClosing = !inlineClosing;
    } else {
        newText += text.charAt(i);
    }
}

document.body.innerHTML = newText;
