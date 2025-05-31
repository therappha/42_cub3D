#!/bin/bash

for file in maps/valid/*.cub; do
    echo "Abrindo: $file"

    ./cub3d "$file" &     # Executa em background
    pid=$!
    wait $pid             # Espera o processo terminar
    exit_code=$?

    if [ $exit_code -eq 139 ]; then
        echo "❌ Segfault detectado no arquivo: $file"
        exit 1
    fi
done

echo "✅ Todos os testes concluídos sem segfault!"

