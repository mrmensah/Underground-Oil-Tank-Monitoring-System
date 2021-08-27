# from django.shortcuts import render
# from rest_framework.renderers import (HTMLFormRenderer, JSONOpenAPIRenderer, BrowsableAPIRenderer)
from django.contrib.auth.models import User, Group
from rest_framework.views import APIView
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework.serializers import Serializer
from rest_framework import viewsets
from rest_framework import permissions
from monitor.models import Data
from monitor.serializers import UserSerializer, GroupSerializer,DataSerializer
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser


# @api_view(['GET', 'POST'])
# def sensor_data(request):
#     "List all data or create new data"
#     if request.method == 'GET':
#         queryset = Data.objects.all()
#         serializer = DataSerializer(queryset, many=True)
#         return Response(serializer.data)

#     elif request.method == 'POST':
#         serializer = DataSerializer(data=request.data)
#         if serializer.is_valid():
#             serializer.save()
#             return Response(serializer.data, status=status.HTTP_201_CREATED)
#         return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)



# class UserViewSet(viewsets.ModelViewSet):
#     """
#     API endpoint that allows users to be viewed or edited.
#     """
#     queryset = User.objects.all().order_by('-date_joined')
#     serializer_class = UserSerializer
#     permission_classes = [permissions.IsAuthenticated]


# class DataViewSet(APIView):
#     def get(self, request, format=None):
#         my_data = Data.objects.all()
#         serializer = DataSerializer(my_data, many=True)
#         return Response(serializer.initial_data)

#     def post(self, request, format=None):
#         serializer = DataSerializer(data=request.data)
#         if serializer.is_valid():
#             serializer.save()
#             return Response(serializer.data, status=201)
#         return Response(serializer.errors, status=400)


# class GroupViewSet(viewsets.ModelViewSet):
#     """
#     API endpoint that allows groups to be viewed or edited.
#     """
#     queryset = Group.objects.all()
#     serializer_class = GroupSerializer
#     permission_classes = [permissions.IsAuthenticated]

@csrf_exempt
def sensors_data(request):
    """
    List all code snippets, or create a new snippet.
    """
    if request.method == 'GET':
        my_data = Data.objects.all()
        serializer = DataSerializer(my_data, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        serializer = DataSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)