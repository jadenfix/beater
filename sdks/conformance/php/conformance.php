<?php

declare(strict_types=1);

// Live conformance: drive the GENERATED PHP control-plane client against a
// running beaterd and verify typed request/response shapes match the API.
//
// Proves API-shape == SDK-shape for PHP. Run via run.sh.

require_once __DIR__ . '/vendor/autoload.php';

use Beater\Client\Api\DatasetsApi;
use Beater\Client\Api\HealthApi;
use Beater\Client\Api\TracesApi;
use Beater\Client\Configuration;
use Beater\Client\Model\CreateDatasetRequest;

$base = rtrim((string) getenv('BEATER_BASE_URL'), '/');
$tenant = getenv('BEATER_TENANT') ?: 'demo';
$project = getenv('BEATER_PROJECT') ?: 'demo';

$config = Configuration::getDefaultConfiguration()->setHost($base);
$http = new GuzzleHttp\Client();

try {
    // 1. health -> typed response
    $health = (new HealthApi($http, $config))->health();
    if ($health->getOk() !== true) {
        throw new RuntimeException('health.ok != true: ' . var_export($health, true));
    }
    echo '  health: ok=' . var_export($health->getOk(), true) . "\n";

    // 2. create dataset -> typed request body + typed response (shape parity)
    $req = new CreateDatasetRequest(['name' => 'conformance-php']);
    $created = (new DatasetsApi($http, $config))->createDataset($tenant, $project, $req);
    echo '  createDataset -> ' . (new ReflectionClass($created))->getShortName() . "\n";

    // 3. list traces -> typed page response
    $page = (new TracesApi($http, $config))->listTraces($tenant);
    if ($page->getItems() === null) {
        throw new RuntimeException('traces.list page missing items: ' . var_export($page, true));
    }
    echo '  traces.list -> ' . (new ReflectionClass($page))->getShortName()
        . ' items=' . count($page->getItems()) . "\n";

    echo "PASS: php generated client round-trips against live API\n";
} catch (Throwable $e) {
    fwrite(STDERR, 'FAIL: ' . get_class($e) . ': ' . $e->getMessage() . "\n");
    exit(1);
}
