from pydantic import BaseModel
from typing import List

class TouchConfig(BaseModel):
    BAUDRATE: int