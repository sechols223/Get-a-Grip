import { WebSocket, WebSocketServer } from "ws";

const PORT = 8085;
const TARGET = "wss://get-a-grip.onrender.com";

var wss = new WebSocketServer({ port: PORT });

wss.on("connection", (ws) => {
  ws.on("error", (e) => console.error("incoming ws:", e));

  const proxyWs = new WebSocket(TARGET);
  proxyWs.on("open", () => {
    ws.on("close", () => proxyWs.close());
    ws.on("message", (data, isBinary) =>
      proxyWs.send(data, { binary: isBinary })
    );
  });

  proxyWs.on("message", (data, isBinary) => {
    ws.send(data, { binary: isBinary });
  });

  proxyWs.on("error", (e) => console.error("proxy ws:", e));
});

console.log('Proxy to "%s" opened on %d!', TARGET, PORT);
