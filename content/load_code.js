// sauce: https://stackoverflow.com/questions/1787322
function escapeHtml(text) {
    let map = {
        "&": "&amp;",
        "<": "&lt;",
        ">": "&gt;",
        // "'": "&quot;",  // these should't be needed in <pre> tags
        // "\"": "&#039;"
    };
    return text.replace(/[&<>]/g, function(m) { return map[m]; });
}

// sauce: https://stackoverflow.com/questions/6348207
let code = new XMLHttpRequest();
let allText = "file not found";
code.onreadystatechange = function () {
    if (code.readyState === XMLHttpRequest.DONE && code.status === 200) {
        allText = code.responseText;
    }
    if (typeof ARGS !== "undefined") {
        let codeStr = `<pre><code class="language-${ARGS.lang()}">${escapeHtml(allText)}</code></pre>`;
        let elem = document.getElementById("code");
        if (elem !== null) {
            elem.innerHTML = codeStr;
        }
    }

    // add prism to the end of the script
    let script = document.createElement("script");
    script.type = "text/javascript";
    script.src = "../../../lib/prism/prism.js";
    // console.log(ARGS.codeFile());
    // console.log(document.getElementsByTagName("head")[0]);
    document.getElementsByTagName("head")[0].appendChild(script);
};

code.open("GET", ARGS.codeFile());
code.send(null);
