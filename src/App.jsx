import React from "react";
import { Route, Routes, useParams } from "react-router-dom";
import CodeViewer from "./components/CodeViewer.jsx";
import p1 from "./programs/p1.c?raw";
import p2 from "./programs/p2.c?raw";
import p3 from "./programs/p3.c?raw";
import p4 from "./programs/p4.c?raw";
import p5 from "./programs/p5.c?raw";
import p6 from "./programs/p6.c?raw";
import p7 from "./programs/p7.c?raw";
import p8 from "./programs/p8.c?raw";
import p9 from "./programs/p9.c?raw";

const programs = { 1: p1, 2: p2, 3: p3, 4: p4, 5: p5, 6: p6, 7: p7, 8: p8, 9: p9 };

function ProgramRoute() {
  const { number } = useParams();
  const source = programs[number];
  return source ? <CodeViewer source={source} /> : <NotFound />;
}

function NotFound() {
  return <main className="not-found">Not found</main>;
}

export default function App() {
  return (
    <Routes>
      <Route path="/api/:number" element={<ProgramRoute />} />
      <Route path="*" element={<NotFound />} />
    </Routes>
  );
}
