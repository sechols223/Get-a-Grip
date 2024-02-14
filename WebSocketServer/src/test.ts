import { afterEach, beforeEach, expect, test } from "@jest/globals";
import { WebSocket, WebSocketServer } from "ws";
import { PORT } from "./constants";
import { setupServer } from "./server";

var wss: WebSocketServer | null = null;

beforeEach(() => {
  wss = setupServer();
});

afterEach(() => {
  wss?.close();
});

test("websockets can communicate", async () => {
  const ws1 = new WebSocket(`ws://localhost:${PORT}`);
  const ws2 = new WebSocket(`ws://localhost:${PORT}`);
  const ws1Open = new Promise((resolve) =>
    ws1.on("open", () => {
      console.log("Web socket 1 opened");
      resolve(undefined);
    })
  );
  const ws2Open = new Promise((resolve) =>
    ws2.on("open", () => {
      console.log("Web socket 2 opened");
      resolve(undefined);
    })
  );
  const received = new Promise((resolve) =>
    ws2.on("message", (data) => resolve(data))
  );

  await ws1Open;
  await ws2Open;
  ws1.send("Test");

  expect(((await received) as Buffer).toString("utf8")).toBe("Test");
  ws1.close();
  ws2.close();
}, 10000);
