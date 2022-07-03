from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from members_component import Leg
from PKDF2_HMAC512 import PKDF2_HMAC512

def test_hash_stable():
    test_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password","random",5)
    hash1 = test_PKDF2_HMAC512.get_hash()
    hash2 = test_PKDF2_HMAC512.get_hash()
    assert hash1 == hash2

def test_hash_unicity():
    test1_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password1","random",5)
    test2_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password2","random",5)
    hash1 = test1_PKDF2_HMAC512.get_hash()
    hash2 = test2_PKDF2_HMAC512.get_hash()
    assert hash1 != hash2

try:
    test_hash_stable()
    test_hash_unicity()
    print("Test OK")
except:
    print("Test KO")
