extends Control

signal submitted(server_address: String)

@export var default_server_address = ""

@onready var server_address_field = %ServerAddressField
@onready var submit_button = %SubmitButton

# Called when the node enters the scene tree for the first time.
func _ready():
	server_address_field.text = default_server_address



func _on_submit_button_pressed():
	submitted.emit(server_address_field.text)
