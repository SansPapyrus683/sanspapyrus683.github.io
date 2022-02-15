// sauce: https://stackoverflow.com/questions/2190801
let ARGS = (function() {
    let _args = {};
    return {
        init: function(args) {
            _args = args;
        },
        codeFile: function() {
            return _args["file"];
        },
        lang: function() {
            return _args["lang"];
        }
    };
}());
