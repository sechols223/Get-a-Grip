extends Control

@onready var loading_indicator = $Panel/LoadingIndicator
@onready var error_indicator = $Panel/ErrorIndicator
@onready var hand_control_anchor = $Panel/HandControlAnchor

var socket = WebSocketPeer.new()
var back_button_pressed = false

# Called when the node enters the scene tree for the first time.
func _ready():
	socket.connect_to_url(WebSocketSettings.server_address)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	socket.poll()
	var state = socket.get_ready_state()
	
	if state == WebSocketPeer.STATE_CONNECTING:
		loading_indicator.show()
		hand_control_anchor.hide()
		error_indicator.hide()
	elif state == WebSocketPeer.STATE_OPEN:
		loading_indicator.hide()
		hand_control_anchor.show()
		error_indicator.hide()
	elif state == WebSocketPeer.STATE_CLOSING:
		pass
	elif state == WebSocketPeer.STATE_CLOSED:
		if back_button_pressed:
			get_tree().change_scene_to_file("res://start_menu.tscn")
			return
		var code = socket.get_close_code()
		if code == -1:
			loading_indicator.hide()
			hand_control_anchor.hide()
			error_indicator.show()
		else:
			pass #todo: handle other close codes

func _on_back_button_pressed():
	back_button_pressed = true
	socket.close()

func _on_hand_control_finger_moved(finger: String, new_value: float):
	if socket.get_ready_state() == WebSocketPeer.STATE_OPEN:
		var data = {
			"finger": finger,
			"angle": new_value * 180.0,
		}
		var data_string = JSON.stringify(data, "  ")
		socket.send_text(data_string)
