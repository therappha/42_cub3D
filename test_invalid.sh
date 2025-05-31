#!/bin/bash

for file in maps/invalid/*.cub; do
    echo "Testando: $file"
    ./cub3D "$file"
    exit_code=$?

    if [ $exit_code -eq 139 ]; then
        echo "❌ Segfault detectado no arquivo: $file"
        exit 1
    fi
done

echo "✅ Todos os testes concluídos sem segfault!"
