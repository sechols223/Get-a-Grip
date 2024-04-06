extends Control

@export var default_server_address := ""

@onready var server_address_entry = $Panel/MenuContainer/ConnectionFormContainer/ServerAddressEntry
@onready var submit_button = $Panel/MenuContainer/ConnectionFormContainer/SubmitButton

# Called when the node enters the scene tree for the first time.
func _ready():
	server_address_entry.text = default_server_address \
		if WebSocketSettings.server_address == "" \
		else WebSocketSettings.server_address

func _on_submit_button_pressed():
	WebSocketSettings.server_address = server_address_entry.text
	get_tree().change_scene_to_file("res://controller_menu.tscn")
