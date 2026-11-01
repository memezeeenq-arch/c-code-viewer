import React from "react";
import hljs from "highlight.js/lib/core";
import c from "highlight.js/lib/languages/c";

hljs.registerLanguage("c", c);

export default function CodeViewer({ source }) {
  const highlighted = hljs.highlight(source, { language: "c" }).value;

  return (
    <pre className="code-viewer">
      <code
        className="language-c"
        dangerouslySetInnerHTML={{ __html: highlighted }}
      />
    </pre>
  );
}
