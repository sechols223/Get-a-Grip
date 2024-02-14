import { WebSocket, WebSocketServer } from "ws";
import { PORT } from "./constants";

export function setupServer() {
  const wss = new WebSocketServer({ port: PORT });

  wss.on("connection", (ws) => {
    ws.on("error", console.error);

    ws.on("message", (data, isBinary) => {
      console.log("received: %s", data);
      // const obj = JSON.parse(data.toString("utf8"));
      wss.clients.forEach((client) => {
        if (client !== ws && client.readyState === WebSocket.OPEN) {
          client.send(data, { binary: isBinary });
        }
      });
    });
  });

  console.log("Web socket server open on port %d!", PORT);
  return wss;
}
