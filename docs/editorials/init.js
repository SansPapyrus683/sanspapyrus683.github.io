// sauce: https://stackoverflow.com/questions/2190801
let ARGS = (function() {
    let _args = {};
    return {
        init: function(args) {
            _args = args;
            let dotInd = _args["file"].lastIndexOf("\.");
            _args["lang"] = _args["file"].slice(dotInd + 1);
        },
        codeFile: function() {
            return _args["file"];
        },
        lang: function() {
            return _args["lang"];
        }
    };
}());
