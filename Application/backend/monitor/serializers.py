from django.contrib.auth.models import User, Group
from rest_framework import serializers
from monitor.models import Data


class UserSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ['url', 'username', 'email']

class DataSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Data
        fields ='__all__'


class GroupSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Group
        fields = ['url', 'name']