# Use a base image with a C development environment
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the C server source code into the container
# we already set the context to the root of the project in the docker-compose file
COPY . .

# Expose the port variable
EXPOSE $C_PORT

# Compile and run the C server program
RUN ./serve.sh
